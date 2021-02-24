# Oasis
#### Video Demo:  https://youtu.be/hwaLB3Odkgc
#### Description:

With all of the stress and responsibilities we face in today’s world, 
many of us turn to the internet for a much-needed break and distraction. 
Oasis allows you to create a custom page with your favorite YouTube playlist, Spotify playlist, 
inspirational quotes, and meditations. Create your own Internet Oasis.

For this project I utilized Flask framework with HTML, CSS, Python, AJAX, JQuery, and Javascript. 


Register:
First I had to implement a login system, so that each users custom settings could be remembered.
For this I utilized code from the previous problem set, written by CS50 staff. 
Application route register accepted 2 methods (Get and Post). With method GET, it 
returned the register.html template. This template, written in HTML, contained a form
which allowed user to submit their username and password. When a user submitted
the form, this sent a POST request to the /register page. In this case, several
conditions were checked using python, to ensure the user's username did not exist already,
passwords matched, and so on. Then the username and password were added to the database. The password was
hashed for security purposes. At this point python would return a redirect to the login page.

Login:
The /login application route, accepted GET and POST methods. With GET method, the login.html 
template was rendered. This contained a form where the user could input username and password. 
With the POST route (as when user submitted the form), Python code was utilized to process the information.
SQL and Python were used to query the database to check if the username and password were valid. If yes, the session 
user id was updated, so user would be remembered as they visted various pages within the website. 
The user was then redirected to the main page.

Main Page:
The "/" application route led to the main page. In Python, various user settings, including their Spotify playlist,
Youtube playlist, background, font were obtained from the SQL database using Python and SQL queries. This information was
passed as variables to index.html, when the index.html template was rendered. Javascript was utilized to change the body background,
as well as the font color. The Javascript used variables passed from the application.py document to do this. Within the HTML, 
the Spotify and Youtube video links were updated in the embed code, based on the variables passed. This would then display the 
user's custom video and playlist.

The main page also displayed a random quote from a quotes table in the database. In python, a random number function was utilized to select a random quote 
from the database based on the quote id number. This quote was passed as a variable, and rendered in the HTML of the index page. A list of quotes was
also passed as a variable. There was a button on the index.html page to change the random quote. When this was pressed, a javascript function was triggered,
in which a random number function generated a number which was used to select a new quote from the list of quotes to display.

The main page had a form in which the user could select a meditation to display. Selecting a mediation, triggered a javascript function. 
Within this function, AJAX was utilized to trigger the python application to render the corresponding html document. In this way this section
of the website could be updated without refreshing the entire webpage. 

Quotes:
The "/quotes application route led to a table of all the quotes (obtained from the SQL database). Via the POST method, users could post additional quotes which 
would be saved to the database. upvote and downvote functions could be called by clicking the upvote and downvote buttons next to each quote. AJAX and Jquery were 
utilized to send this information to the server, update the quotes database, and update the total rating displayed, without having to refresh the entire page. 
