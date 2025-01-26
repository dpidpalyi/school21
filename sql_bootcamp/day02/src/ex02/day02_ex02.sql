SELECT COALESCE(p.name, '-') AS person_name,
  v.visit_date AS visit_date,
  COALESCE(piz.name, '-') AS pizzeria_name
FROM (
    SELECT *
    FROM person_visits
    WHERE visit_date BETWEEN '2022-01-01' AND '2022-01-03'
  ) AS v
  FULL JOIN person AS p ON p.id = v.person_id
  FULL JOIN pizzeria AS piz ON piz.id = v.pizzeria_id
ORDER BY person_name,
  visit_date,
  pizzeria_name;