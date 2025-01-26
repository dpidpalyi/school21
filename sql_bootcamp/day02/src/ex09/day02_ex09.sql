SELECT p.name
FROM person AS p
  JOIN person_order AS po ON po.person_id = p.id
  JOIN menu AS m ON po.menu_id = m.id
WHERE p.gender = 'female'
  AND m.pizza_name IN ('pepperoni pizza', 'cheese pizza')
GROUP BY p.name
HAVING COUNT(DISTINCT m.pizza_name) = 2
ORDER BY p.name;