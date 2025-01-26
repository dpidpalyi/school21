SELECT piz.name
FROM pizzeria AS piz
  JOIN person_visits AS v ON v.pizzeria_id = piz.id
  JOIN person ON v.person_id = person.id
  JOIN menu ON v.pizzeria_id = menu.pizzeria_id
WHERE person.name LIKE 'Dmitriy'
  AND v.visit_date = '2022-01-08'
  AND menu.price < 800;