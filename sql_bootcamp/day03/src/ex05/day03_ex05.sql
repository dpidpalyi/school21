WITH cte_visits AS (
  SELECT pz.name AS pizzeria_name
  FROM pizzeria AS pz
    JOIN person_visits AS pv ON pv.pizzeria_id = pz.id
    JOIN person AS p ON pv.person_id = p.id
  WHERE p.name = 'Andrey'
),
cte_order AS (
  SELECT pz.name AS pizzeria_name
  FROM pizzeria AS pz
    JOIN menu AS m ON m.pizzeria_id = pz.id
    JOIN person_order AS po ON po.menu_id = m.id
    JOIN person AS p ON po.person_id = p.id
  WHERE p.name = 'Andrey'
)

SELECT pizzeria_name
FROM cte_visits
EXCEPT
SELECT pizzeria_name
FROM cte_order