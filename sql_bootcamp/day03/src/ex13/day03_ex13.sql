DELETE FROM person_order
WHERE order_date = '2022-02-25'
    AND menu_id = (
        SELECT id
        FROM menu
        WHERE pizza_name = 'greek pizza'
    );
DELETE FROM menu
WHERE pizza_name = 'greek pizza';
--SELECT * FROM person_order;