WITH cte_male AS (
  (
    SELECT pz.name AS pizzeria_name
    FROM pizzeria AS pz
      JOIN person_visits AS pv ON pv.pizzeria_id = pz.id
      JOIN person AS p ON pv.person_id = p.id
    WHERE p.gender = 'male'
  )
  EXCEPT ALL (
      SELECT pz.name AS pizzeria_name
      FROM pizzeria AS pz
        JOIN person_visits AS pv ON pv.pizzeria_id = pz.id
        JOIN person AS p ON pv.person_id = p.id
      WHERE p.gender = 'female'
    )
),
cte_female AS (
  (
    SELECT pz.name AS pizzeria_name
    FROM pizzeria AS pz
      JOIN person_visits AS pv ON pv.pizzeria_id = pz.id
      JOIN person AS p ON pv.person_id = p.id
    WHERE p.gender = 'female'
  )
  EXCEPT ALL (
      SELECT pz.name AS pizzeria_name
      FROM pizzeria AS pz
        JOIN person_visits AS pv ON pv.pizzeria_id = pz.id
        JOIN person AS p ON pv.person_id = p.id
      WHERE p.gender = 'male'
    )
)

SELECT pizzeria_name
FROM cte_male
UNION
SELECT pizzeria_name
from cte_female
ORDER BY pizzeria_name;