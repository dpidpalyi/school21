SELECT p.name
FROM person AS p
  JOIN person_order AS po ON po.person_id = p.id
  JOIN menu AS m ON po.menu_id = m.id
WHERE p.gender = 'male'
  AND p.address IN ('Moscow', 'Samara')
  AND m.pizza_name IN ('pepperoni pizza', 'mushroom pizza')
ORDER BY p.name DESC;