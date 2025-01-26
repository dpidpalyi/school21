CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop INT = 10)
RETURNS TABLE(num INT) AS $$
BEGIN
    RETURN QUERY
    WITH RECURSIVE cte(n1, n2) AS (
        VALUES (0, 1)
        UNION ALL
        SELECT n2,
            n1 + n2
        FROM cte
        WHERE n2 < pstop
    )
    SELECT n1
    FROM cte;
END;
$$ LANGUAGE PLPGSQL;

SELECT *
FROM fnc_fibonacci(100);

SELECT *
FROM fnc_fibonacci();