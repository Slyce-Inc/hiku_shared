#!/usr/local/bin/python2.7

def main():
    pass

if __name__ == '__main__':
    main()

import MySQLdb
import cgitb
import json
import cgi
from rtm import createRTM

##################################################################
## 2014/02/20 Rajan Bala                                        ##
##                                                              ##
## This script functions as a webhook which receives posts from ##
## Hiku for Remember The Milk                                   ##
##################################################################

# This function will open up the DB for use, this is if you have
# local database that you want to look up the hiku token associated with
# your users
# @return the conn object of the DB
def openDB():
	# open database connection
	# open db connections
	conn = MySQLdb.connect (host = "yourHost",
							user = "yourUserName",
							passwd = "yourPassword",
							db = "yourDataBase")
	return conn;

#This function will close the database associated with the connection
#@param conn: the connection object to be closed
def closeDB(conn, curs):
	# now close the conn and curs out
	curs.close()
	conn.close()

# This function will get the 3rd Party token provided the internal token
# associated with the 3rd party app
# @param hikuToken: the token associated with the RTM token
def getRTMToken(hikuToken):
	conn = openDB()
	curs = conn.cursor()
	result = "undefined"
	try:
	
		# using your database, get the local user information provided the hiku token
		curs.execute('SELECT * FROM userTable WHERE hiku_token=%s AND app_type=%s',(hikuToken,"rtm"))
		for row in curs:
			result = row[0]
		
		conn.commit()
		
	except conn.Error, e:
		result = "exception"
	
	# close the DB before getting out
	closeDB(conn, curs)
	return result

    
def sendToRTM (token, task, audioPath):
    apiKey='yourApiKey'
    secret='yourSecret'
    
    
    try: 
        rtm = createRTM(apiKey, secret, token)
    except Exception,e:
       return {'name': 'error', 'errVal': str(e)}

    try: 
        rspTimeline = rtm.timelines.create()
    except Exception,e:
       return {'name': 'error', 'errVal': str(e)}

    if hasattr(rspTimeline, "timeline"):
        # hardcode #Beepit tag to distinguish it in the RTM list
        # parse =1 tells rtm to use smartadd and parse # as a tag or list name
        # if list or tag exists, then task is put in it, otherwise a new tag
        # is created
        taskName = task +' #hiku '
        if (audioPath):
            print 'audioPath = ' + audioPath
            #taskName = taskName " '" + audioPath + " '"
	    taskName = ' ' + audioPath + ' ' + taskName
        print 'task sending to rtm' 
        print taskName
        rspTaskAdd = rtm.tasks.add(timeline=rspTimeline.timeline, name=taskName, parse=1)

    return {'name': 'success', 'rtmstatus': str(rspTaskAdd)}   
		

# activate a special exception handler that will display detailed
# reports in the Web browser if any errors occur
cgitb.enable()

print "Content-type: application/json"
print                               # blank line, end of headers

# get parameters
form = cgi.FieldStorage()
# below is where we retrieve all the parameters passed in by the server


# below is where I get the token 
data = form.getfirst("data")
#f = open('debug.txt',"wb")
#f.write(data)
#f.close()

data = json.loads(data)
hikuToken = data['token'] 
rtmToken = getRTMToken(hikuToken)
result = {"name":"success"}


if( rtmToken != "undefined" and rtmToken != "exception" ):
    # We have an RTM Token, lets deal with it
    # Construct the params = {}
    #{"ean":"025700003915","name":"Ziploc Sandwhich Bags 100 ct", "path": null, "token": "DYUUXx6lX8yPEzPClbj6U2YWlo5ej4g0"}	
    result = sendToRTM(rtmToken,data['name'], data['audioPath']) 
    
else:
    # we either have an exception or it doesn't exist, lets deal with it
    result = {"name":"error", "message":"rtmToken undefined"} 
    
resultSet = json.dumps( result )
print resultSet
