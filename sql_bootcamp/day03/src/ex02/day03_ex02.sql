SELECT pizza_name,
  price,
  name
FROM menu
  JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
WHERE menu.id IN (
    SELECT menu.id
    FROM menu
    EXCEPT
    SELECT menu_id
    FROM person_order
  )
ORDER BY pizza_name,
  price;