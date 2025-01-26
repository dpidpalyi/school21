#!/bin/sh
gcc /app/fcgi_app.c -o /app/fcgi_app -lfcgi
spawn-fcgi -p 8080 -n /app/fcgi_app &
