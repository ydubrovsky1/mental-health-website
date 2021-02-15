import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    #get the individual's username
    placeholder = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    username = placeholder[0]["username"]
    
    #use individual's username to retrieve data from portfolio and user databases
    portfolio = db.execute("SELECT id, symbol, shares, price, total FROM portfolio WHERE username = ?", username)
    users = db.execute("SELECT id, cash FROM users WHERE username = ?", username)
    
    #live update values of the stocks, and the total value of each stock
    for row in portfolio:
        ID = row["id"]
        symbol = row["symbol"]
        shares = row["shares"]
        value = lookup(symbol)["price"]
        total_value = value * shares 
        if shares > 0:
            db.execute("UPDATE portfolio SET price = ?, total = ? WHERE id = ?", value, total_value, ID)
        
    
    #calculate users total value stocks+cash
    cash = float(users[0]["cash"])
    total = float(cash)
    for row in portfolio:
        total += float(row["total"])
    
    #display user portfolio
    portfolio1 = db.execute("SELECT symbol, SUM(shares), price, SUM(total) FROM portfolio WHERE username = ? GROUP BY symbol", username)
    return render_template("index.html", portfolio1=portfolio1, users=users, total = total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    
    #if user method was POST (via submitting the Buy form):
    if request.method == "POST":
        """Buy shares of stock"""
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        result1 = lookup(symbol)
        
        # ensure number of stocks greater than 0
        if int(shares) < 1:
            return apology("please enter positive number of stocks to buy")
            
        # ensure stock exists
        elif not lookup(symbol):
            return apology("stock not found")
        
        # calculate variables for the portfolio
        else:
            cash_key = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            
            cash = float(cash_key[0]["cash"])
            price = result1["price"]
            total = float (price) * float(shares)
            funds = cash - total
            
            #ensure user has sufficient funds
            if total > cash:
                return apology("insufficient funds")
                
            #lookup username
            placeholder = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
            username = placeholder[0]["username"]
            
            
            #update users total cash remaining
            db.execute("UPDATE users SET cash = ? WHERE username = ?", funds, username)
            
            #add a new entry to the database, including datetime
            date = datetime.now()
            db.execute("INSERT INTO portfolio (username, symbol, shares, price, total, funds, Date) VALUES (?,?,?, ?, ?, ?, ?)", username, symbol, shares, price, total, funds, date)
            
            
            return redirect("/")
    else:
        return render_template("buy.html")
  


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    #get the individual's username
    placeholder = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    username = placeholder[0]["username"]
    
    #use individual's username to retrieve data from portfolio
    portfolio = db.execute("SELECT id, symbol, shares, price, total, Date FROM portfolio WHERE username = ?", username)

    #display user portfolio
    return render_template("history.html", portfolio=portfolio)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        result = lookup(symbol)
        return render_template("quoted.html", result = result)
    
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting form via POST)
    if request.method == "POST":
        
        #Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)
            
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)
            
        #Ensure password and confirmation match
        elif request.form.get("password") != request.form.get("confirmation"):
             return apology("password and confirmation do not match", 403)
            
        #Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        #Ensure username does not exist
        if len(rows) == 1:
            return apology("username already exists.")
        #Add username and password to database
        else:
            username = request.form.get("username")
            password1 = request.form.get("password")
            password = generate_password_hash(password1, method='pbkdf2:sha256', salt_length=8)
            rows = db.execute("INSERT INTO users (username, hash) VALUES (?,?)", username, password)
        
        # Redirect user to home page so they can log in
        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    #retrieve the list of user's stocks 
    placeholder = db.execute("SELECT username, cash FROM users WHERE id = ?", session["user_id"])
    username = placeholder[0]["username"]
    cash = placeholder[0]["cash"]
    portfolio = db.execute("SELECT DISTINCT symbol FROM portfolio WHERE username = ?", username)
    
    #if user submits stocks to sell
    if request.method == "POST":
        
        #ensure user input positive number
        shares = int(request.form.get("shares"))
        if shares < 1:
            return apology("Please select positive number of shares.")
        
        #get information for those stocks
        symbol = request.form.get("symbol")
        portfolio = db.execute("SELECT symbol, shares, price, total FROM portfolio WHERE symbol = ? GROUP BY symbol", symbol)
        
        #check that user has sufficient stocks
        remainder = (portfolio[0]["shares"]) - shares
        if remainder < 0:
            return apology("You do not have that many shares.")
        
        #if user is selling some shares, update portfolio and user db
        else:
            #get current value of stocks
            value = lookup(symbol)["price"]
            overall_value = float(value) * shares
            
            #update users total cash
            update = cash + overall_value
            db.execute("UPDATE users SET cash = ? WHERE username = ?", update, username)
            
            #add a new entry to the database, including datetime, make negative what needs be negative
            neg_shares = -shares
            neg_value = -overall_value
            date = datetime.now()
            db.execute("INSERT INTO portfolio (username, symbol, shares, price, total, Date) VALUES (?,?,?, ?, ?, ?)", username, symbol, neg_shares, value, neg_value, date)
            
        return redirect("/")
            
    else:
        return render_template("sell.html", portfolio = portfolio)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
