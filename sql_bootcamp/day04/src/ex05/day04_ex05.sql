CREATE VIEW v_price_with_discount AS
SELECT p.name,
  m.pizza_name,
  m.price,
  CAST(m.price * 0.9 AS INT) AS discount_price
FROM person AS p
  JOIN person_order AS po ON po.person_id = p.id
  JOIN menu AS m ON po.menu_id = m.id
ORDER BY p.name,
  m.pizza_name;
--SELECT *
--FROM v_price_with_discount;