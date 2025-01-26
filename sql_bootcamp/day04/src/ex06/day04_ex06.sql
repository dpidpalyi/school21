CREATE MATERIALIZED VIEW mv_dmitriy_visits_and_eats AS
SELECT pz.name
FROM pizzeria AS pz
  JOIN person_visits AS v ON v.pizzeria_id = pz.id
  JOIN person ON v.person_id = person.id
  JOIN menu ON v.pizzeria_id = menu.pizzeria_id
WHERE person.name = 'Dmitriy'
  AND v.visit_date = '2022-01-08'
  AND menu.price < 800;
--SELECT * FROM mv_dmitriy_visits_and_eats;