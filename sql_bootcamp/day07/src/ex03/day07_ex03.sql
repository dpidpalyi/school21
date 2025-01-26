WITH cte(name, cnt) AS (
    (
        SELECT pz.name,
            COUNT(pz.id)
        FROM person_order AS po
            JOIN menu AS m ON po.menu_id = m.id
            JOIN pizzeria AS pz ON pz.id = m.pizzeria_id
        GROUP BY pz.name
    )
    UNION ALL
    (
        SELECT pz.name,
            COUNT(pv.id)
        FROM person_visits AS pv
            JOIN pizzeria AS pz ON pv.pizzeria_id = pz.id
        GROUP BY pz.name
    )
)
SELECT name,
    SUM(cnt) AS total_count
FROM cte
GROUP BY name
ORDER BY total_count DESC,
    name;

--WITH cte_o AS (
--SELECT pz.name,
--COUNT(pz.id)
--FROM person_order AS po
--JOIN menu AS m ON po.menu_id = m.id
--JOIN pizzeria AS pz ON pz.id = m.pizzeria_id
--GROUP BY pz.name
--),
--cte_v AS (
--SELECT pz.name,
--COUNT(pv.id)
--FROM person_visits AS pv
--JOIN pizzeria AS pz ON pv.pizzeria_id = pz.id
--GROUP BY pz.name
--)
--SELECT COALESCE(cte_o.name, cte_v.name) AS name,
--COALESCE(cte_o.count, 0) + COALESCE(cte_v.count, 0) AS total_count
--FROM cte_o
--FULL JOIN cte_v ON cte_o.name = cte_v.name
--ORDER BY total_count DESC, cte_o.name;