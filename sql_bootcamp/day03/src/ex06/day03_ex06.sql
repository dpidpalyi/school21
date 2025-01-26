WITH cte AS (
  SELECT m.id,
    m.pizza_name,
    pz.name,
    m.price
  FROM menu AS m
    JOIN pizzeria AS pz ON pz.id = m.pizzeria_id
)

SELECT cte_1.pizza_name,
  cte_1.name AS pizzeria_name_1,
  cte_2.name AS pizzeria_name_2,
  cte_1.price
FROM cte AS cte_1
  JOIN cte AS cte_2 ON cte_1.pizza_name = cte_2.pizza_name
  AND cte_1.price = cte_2.price
  AND cte_1.id > cte_2.id
ORDER BY pizza_name;