import os 

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required

from datetime import datetime

import random

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
    
# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///oasis.db")

@app.route("/upvote", methods=["POST"])
def upvote_post():
    quoteid = int(request.form['rowid'])
    db.execute("UPDATE quotes SET rating = rating + 1 WHERE id = ?", quoteid)
    quote = str(db.execute("SELECT rating FROM quotes WHERE id = ?", quoteid)[0]["rating"])
    return quote
    
@app.route("/downvote", methods=["POST"])
def downvote_post():
    quoteid = int(request.form['rowid'])
    db.execute("UPDATE quotes SET rating = rating - 1 WHERE id = ?", quoteid)
    quote = str(db.execute("SELECT rating FROM quotes WHERE id = ?", quoteid)[0]["rating"])
    return quote

@app.route("/Depression", methods=["GET", "POST"])
def depression():
    return render_template("depression.html")
    
@app.route("/Bodyscan", methods=["GET", "POST"])
def bodyscan():
    return render_template("bodyscan.html")
    
@app.route("/Basics", methods=["GET", "POST"])
def basics():
    return render_template("Basics.html")

@app.route("/meditation")
@login_required
def meditation():
    """Meditation Page"""
    #display the webpage
    return render_template("meditation.html")

@app.route("/quotes", methods=["GET", "POST"])
@login_required
def route():
    """Quotes Display Page"""
    # get the quotes database
    quotes = db.execute("SELECT id, quote, rating FROM quotes ORDER BY rating DESC")
    
    if request.method == "POST":
        quote = request.form.get("quote")
        db.execute("INSERT INTO quotes (quote) VALUES (?)", quote)
        return redirect("/quotes")
    else:
        #display the table of quotes
        return render_template("quotes.html", quotes=quotes)

@app.route("/customize", methods=["GET", "POST"])
@login_required
def customize():
    """Customization Page"""
    if request.method == "POST":
        # get the individual's username
        placeholder = db.execute("SELECT username, Playlist FROM users WHERE id = ?", session["user_id"])
        username = placeholder[0]["username"]
    
        # update individuals Youtube playlist setting, if appropriate
        if request.form.get("Playlist"):
            playlist = request.form.get("Playlist")
            #update playlist setting in database
            db.execute("UPDATE users SET Playlist = ? WHERE username = ?", playlist, username)
        
        #update individuals Spotify if appropriate
        if request.form.get("Spotify"):
            Spotify = request.form.get("Spotify")
            #update playlist setting in database
            db.execute("UPDATE users SET Spotify = ? WHERE username = ?", Spotify, username)
            
        #update individuals background if appropriate
        if request.form.get("Background"):
            Background = request.form.get("Background")
            #update playlist setting in database
            db.execute("UPDATE users SET Background = ? WHERE username = ?", Background, username)
            
        #update individuals font color if appropriate
        if request.form.get("Color"):
            color = request.form.get("Color")
            #update playlist setting in database
            db.execute("UPDATE users SET Font = ? WHERE username = ?", color, username)
            
    
        return redirect("/")
    else:
        # display customize page
        return render_template("customize.html")    

@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Oasis Mainpage"""
    # get the individual's username, Youtube, Spotify, Background, Font
    placeholder = db.execute("SELECT username, Playlist, Spotify, Background, Font FROM users WHERE id = ?", session["user_id"])
    username = placeholder[0]["username"]
    playlist = placeholder[0]["Playlist"]
    Spotify = placeholder[0]["Spotify"]
    Background = placeholder[0]["Background"]
    Font = placeholder[0]["Font"]
    playlist_youtube = "https://www.youtube.com/embed/?listType=playlist&list=" + playlist
    playlist_spotify = "https://open.spotify.com/embed/playlist/"+ Spotify
    
    # get the users random quote
    a = random.randint(1, 3)
    quotesdatabase = db.execute("SELECT quote FROM quotes")
    quote_1 = db.execute("SELECT id, quote, rating FROM quotes WHERE id = ?", a)
    quote = quote_1[0]["quote"]
    
    # get a list of all the quotes
    quotes = []
    for item in quotesdatabase:
        quotes.append(item["quote"])
    size = len(quotes)
    # display user mainpage
    return render_template("index.html", Youtube=playlist_youtube, quote=quote, quotes=quotes, size=size, Spotify=playlist_spotify, Background=Background, Font=Font)
    
    
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
    

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting form via POST)
    if request.method == "POST":
        
        #Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)
            
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)
            
        #Ensure password and confirmation match
        elif request.form.get("password") != request.form.get("confirmation"):
             return apology("password and confirmation do not match", 400)
            
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
        

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
