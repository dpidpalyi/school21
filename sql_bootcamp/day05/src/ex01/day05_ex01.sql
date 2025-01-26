SET enable_seqscan TO OFF;
EXPLAIN ANALYZE
SELECT m.pizza_name,
    p.name AS pizzeria_name
FROM menu AS m
    JOIN pizzeria AS p ON m.pizzeria_id = p.id;

SET enable_seqscan TO ON;
EXPLAIN ANALYZE
SELECT m.pizza_name,
    p.name AS pizzeria_name
FROM menu AS m
    JOIN pizzeria AS p ON m.pizzeria_id = p.id;