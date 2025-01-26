WITH cte(address, formula, average) AS (
    SELECT address,
        ROUND((MAX(age) - (MIN(age) * 1.0 / MAX(age))), 2),
        ROUND(AVG(age), 2)
    FROM person
    GROUP BY address
    ORDER BY address
)
SELECT address,
    formula,
    average,
    CASE
        WHEN formula > average THEN TRUE
        ELSE FALSE
    END AS comparison
FROM cte;