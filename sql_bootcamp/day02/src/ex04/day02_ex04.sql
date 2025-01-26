SELECT pizza_name,
  name AS pizzeria_name,
  price
FROM (
    SELECT *
    FROM menu
    WHERE pizza_name IN ('mushroom pizza', 'pepperoni pizza')
  ) AS menu
  JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
ORDER BY pizza_name,
  pizzeria_name;