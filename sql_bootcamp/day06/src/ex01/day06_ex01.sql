INSERT INTO person_discounts
SELECT ROW_NUMBER() OVER () AS id,
    p.person_id,
    m.pizzeria_id,
    CASE
        (COUNT(p.person_id))
        WHEN 1 THEN 10.5
        WHEN 2 THEN 22
        ELSE 30
    END AS discount
FROM person_order AS p
    JOIN menu AS m ON m.id = p.menu_id
GROUP BY p.person_id,
    m.pizzeria_id
ORDER BY p.person_id;