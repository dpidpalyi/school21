SELECT m.pizza_name,
  piz.name AS pizzeria_name
FROM person_order AS po
  JOIN (
    SELECT id
    FROM person
    WHERE name IN ('Denis', 'Anna')
  ) AS person ON po.person_id = person.id
  JOIN menu AS m ON po.menu_id = m.id
  JOIN pizzeria AS piz ON m.pizzeria_id = piz.id
ORDER BY pizza_name,
  pizzeria_name;