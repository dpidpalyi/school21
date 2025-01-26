WITH cte_male AS (
  (
    SELECT pz.name AS pizzeria_name
    FROM pizzeria AS pz
      JOIN menu AS m ON m.pizzeria_id = pz.id
      JOIN person_order AS po ON po.menu_id = m.id
      JOIN person AS p ON po.person_id = p.id
    WHERE p.gender = 'male'
  )
  EXCEPT (
      SELECT pz.name AS pizzeria_name
      FROM pizzeria AS pz
        JOIN menu AS m ON m.pizzeria_id = pz.id
        JOIN person_order AS po ON po.menu_id = m.id
        JOIN person AS p ON po.person_id = p.id
      WHERE p.gender = 'female'
    )
),
cte_female AS (
  (
    SELECT pz.name AS pizzeria_name
    FROM pizzeria AS pz
      JOIN menu AS m ON m.pizzeria_id = pz.id
      JOIN person_order AS po ON po.menu_id = m.id
      JOIN person AS p ON po.person_id = p.id
    WHERE p.gender = 'female'
  )
  EXCEPT (
      SELECT pz.name AS pizzeria_name
      FROM pizzeria AS pz
        JOIN menu AS m ON m.pizzeria_id = pz.id
        JOIN person_order AS po ON po.menu_id = m.id
        JOIN person AS p ON po.person_id = p.id
      WHERE p.gender = 'male'
    )
)

SELECT pizzeria_name
FROM cte_male
UNION
SELECT pizzeria_name
FROM cte_female
ORDER BY pizzeria_name;