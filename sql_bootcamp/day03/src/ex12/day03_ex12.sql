INSERT INTO person_order
SELECT (
    SELECT MAX(id)
    FROM person_order
  ) + p.id,
  p.id,
  (
    SELECT menu.id
    FROM menu
    WHERE pizza_name = 'greek pizza'
  ),
  '2022-02-25'
FROM person AS p;
--SELECT * FROM person_order;