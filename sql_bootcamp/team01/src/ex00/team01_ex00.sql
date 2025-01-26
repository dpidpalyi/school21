WITH b AS (
    SELECT user_id, 
        type,
        SUM(money) AS volume,
        currency_id
    FROM balance
    GROUP BY user_id,
        type,
        currency_id
),
c AS (
    SELECT currency.id,
        name,
        rate_to_usd
    FROM currency
        JOIN (
            SELECT id,
                MAX(updated) AS upd
            FROM currency
            GROUP BY id
        ) AS mx ON currency.id = mx.id
        AND currency.updated = mx.upd
)

SELECT COALESCE(u.name, 'not defined') AS name,
    COALESCE(u.lastname, 'not defined') AS lastname,
    b.type,
    b.volume,
    COALESCE(c.name, 'not defined') AS currency_name,
    COALESCE(c.rate_to_usd, 1) AS last_rate_to_usd,
    ROUND(b.volume * COALESCE(c.rate_to_usd, 1)) AS total_volume_in_usd
FROM b
    FULL JOIN "user" AS u ON u.id = b.user_id
    FULL JOIN c ON b.currency_id = c.id
ORDER BY name DESC,
    lastname,
    type;