#!/usr/bin/python
# -*- coding: latin-1 -*-
import os
import sys
import datetime
import requests
import time
import csv
import cgitb
import json
import sys
import cgi
import base64
import hashlib
import datetime
import httplib, urllib,urllib2, cookielib


APP_ID = '<enteryourappidhere>'
SHARED = '<enteryoursharedhere>'
TOKEN = '<enteryourusertokenhere>'

HOST = "app.hiku.us"
BASE_URL = "https://"+HOST
BASE_URL = BASE_URL+"/api/v1/list"


class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
            
            

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
def addAPIParams(params, app_id, shared):
    time = str(datetime.datetime.utcnow()) # get the utc time to generate the signature
    sig = createSignature(time, app_id, shared)
    params['time'] = time
    params['sig'] = sig
    params['app_id'] = app_id
    return params

# This function fetches the list of a user from the hiku cloud
# @return the response from the server, it would either contain a list JSON
#         if successful, otherwise an error JSON
def getList(token):
    param = {}
    
    param = addAPIParams(param,APP_ID, SHARED)
    headers = {"Content-type": "application/x-www-form-urlencoded", "Accept": "application/json"}
    method="GET"
    param = urllib.urlencode(param)
    ch = httplib.HTTPSConnection(HOST)
    ch.request(method, BASE_URL, param, headers)
    response = ch.getresponse()
    data = json.loads(response.read())
    data = data["response"]
    if( 'status' in data and data["status"] == "ok"):
        return data["data"]
    return None


def test():
    
    print getList(TOKEN)

if __name__ == '__main__':
    test()
