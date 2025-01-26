FROM nginx

COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
COPY ./app /app
COPY ./fcgi_app.sh /docker-entrypoint.d

RUN apt-get update -y && apt-get install -y \
    gcc \
    libfcgi-dev \
    spawn-fcgi \
    && rm -rf /var/lib/apt/lists/* \
    chown -R nginx:nginx /etc/nginx/nginx.conf; \
    chown -R nginx:nginx /app/; \
    chown -R nginx:nginx /docker-entrypoint.d/; \
    chown -R nginx:nginx /var/cache/nginx; \
    touch /var/run/nginx.pid; \
    chown -R nginx:nginx /var/run/nginx.pid

CMD ["nginx", "-g", "daemon off;"]

USER nginx

ENTRYPOINT ["/docker-entrypoint.sh"]

