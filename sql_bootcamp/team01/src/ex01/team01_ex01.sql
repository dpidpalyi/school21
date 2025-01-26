INSERT INTO currency VALUES (100, 'EUR', 0.85, '2022-01-01 13:29');
INSERT INTO currency VALUES (100, 'EUR', 0.79, '2022-01-08 13:29');

CREATE OR REPLACE FUNCTION get_rate(pid INT, pupd TIMESTAMP) RETURNS NUMERIC AS $$
BEGIN
    RETURN 
    (SELECT rate_to_usd FROM(
    (SELECT rate_to_usd, updated
     FROM currency
     WHERE id = pid AND EXTRACT(EPOCH FROM ((pupd - updated))) >= 0
     ORDER BY updated DESC
     LIMIT 1)
     UNION
     (SELECT rate_to_usd, updated
     FROM currency
     WHERE id = pid AND EXTRACT(EPOCH FROM ((pupd - updated))) < 0
     ORDER BY updated
     LIMIT 1)
     ORDER BY updated
     LIMIT 1));
END;
$$ LANGUAGE PLPGSQL;

SELECT COALESCE(u.name, 'not defined') AS name,
    COALESCE(u.lastname, 'not defined') AS lastname,
    c.name AS currency_name,
    ROUND(b.money * get_rate(b.currency_id, b.updated), 2) AS currency_in_usd
FROM balance AS b
    FULL JOIN "user" AS u ON b.user_id = u.id
    RIGHT JOIN (SELECT DISTINCT id, name FROM currency) AS c ON b.currency_id = c.id
ORDER BY name DESC, lastname, currency_name;
