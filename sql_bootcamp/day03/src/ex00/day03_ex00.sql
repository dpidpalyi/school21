SELECT m.pizza_name,
    m.price,
    pz.name,
    v.visit_date
FROM person_visits AS v
    JOIN person ON v.person_id = person.id
    JOIN pizzeria AS pz ON v.pizzeria_id = pz.id
    JOIN menu AS m ON pz.id = m.pizzeria_id
WHERE person.name = 'Kate'
    AND m.price BETWEEN 800 AND 1000
ORDER BY pizza_name,
    price,
    pizza_name;