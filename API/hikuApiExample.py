#!/usr/local/bin/python2.7

def main():
    pass

if __name__ == '__main__':
    main()

import MySQLdb
import cgitb
import json
import cgi
import base64
import hashlib
import datetime
import httplib, urllib,urllib2, cookielib

# Definitions for your app
APP_ID = 'yourAppId'
SHARED = 'yourShared'

HOST = "hiku.herokuapp.com"
BASE_URL = "https://"+HOST
BASE_URL = BASE_URL+"/api/v1/apps"

##################################################################
## 2014/02/20 Rajan Bala (rajan@hiku.us)                        ##
## This is an example code for showing third parties to be able ##
## to integrate into hiku to receive hiku notifications(beeps)  ##
## If you are looking for how the webhook works to receive      ##
## notifications, please refer to the webhook example           ##
##################################################################

#This function creates the signature provided the time, app_id, and shared secret.
#
#@param time in utc format
#@param app_id provided by hiku for your application
#@param shared secrect provided hiku for your application
#
#@return signature string generated using sha256 following hiku API definition
def createSignature(time, app_id, shared):
    sig=app_id+shared+time
    sig=hashlib.sha256(sig).hexdigest()
    return sig

#This function takes in user generated params and adds the basic api required paramters by generating the signature
#
#@param user parameter dictionary
#@return dictionary with api parameters
def addAPIParams(params):
    time = str(datetime.datetime.utcnow()) # get the utc time to generate the signature
    sig = createSignature(time, APP_ID, SHARED)
    params['time'] = time
    params['sig'] = sig
    params['app_id'] = APP_ID
    return params

# This function fetches the FROB from the server
# @return the response from the server, it would either contain a FROB JSON
#         if successful, otherwise an error JSON
def getFrob():
    param = {}
    
    param = addAPIParams(param)
    headers = {"Content-type": "application/x-www-form-urlencoded", "Accept": "application/json"}
    method="POST"
    param = urllib.urlencode(param)
    ch = httplib.HTTPSConnection(HOST)
    ch.request(method, BASE_URL, param, headers)
    response = ch.getresponse()
    data = response.read();
    return data


#This function checks the status of the app authentication once the user was presented with the
#barcode obtained from getFrob. Polling on the check status would returne, whether the app is authenticated
#or not
#
#@return app authentication status, or error messages as a JSON
def checkStatus(frob):
    path= BASE_URL+"/"+frob

    param = {}
    param = addAPIParams(param)
    method="PUT"
    headers = {"Content-type": "application/x-www-form-urlencoded", "Accept": "application/json"}
    param = urllib.urlencode(param)
    #ch = httplib.HTTPSConnection("hiku-staging.herokuapp.com")
    ch = httplib.HTTPSConnection("hiku.herokuapp.com")
    ch.request(method, path, param, headers)
    response = ch.getresponse()
    data = response.read();
    return data

# activate a special exception handler that will display detailed
# reports in the Web browser if any errors occur
cgitb.enable()

print "Content-type: application/json"
print                               # blank line, end of headers

# get the FROB, if the data["status"] is okay that means
# you have obtained a valid frob
result = getFrob()
result = json.loads(result)
result = result["response"]


# once you've presented the barcode embedded in the getFrob,
# you can check the status of authentication by calling checkStatus
# assuming the user has scanned the barcode using the hiku device
if( result["status"] == "ok"):
    data = result["data"]
    print checkStatus(data["frob"])
else:
    print result
