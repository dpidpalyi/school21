SELECT p.name,
    m.pizza_name,
    m.price,
    ROUND(m.price * (100.0 - pd.discount) / 100) AS discount_price,
    pz.name AS pizzeria_name
FROM person as p
    JOIN person_order AS po ON p.id = po.person_id
    JOIN menu AS m ON po.menu_id = m.id
    JOIN pizzeria AS pz ON m.pizzeria_id = pz.id
    JOIN person_discounts AS pd ON p.id = pd.person_id
    AND pd.pizzeria_id = pz.id
ORDER BY p.name,
    m.pizza_name;