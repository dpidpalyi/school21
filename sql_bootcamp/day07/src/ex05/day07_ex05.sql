SELECT DISTINCT p.name
FROM person AS p
    JOIN person_order AS po ON po.person_id = p.id
ORDER BY p.name;