(SELECT pz.name,
    COUNT(pz.id),
    'order' AS action_type
FROM person_order AS po
JOIN menu AS m ON po.menu_id = m.id
JOIN pizzeria AS pz ON pz.id = m.pizzeria_id
GROUP BY pz.name
ORDER BY count DESC
LIMIT 3)
UNION
(SELECT pz.name,
    COUNT(pv.id),
    'visit' AS action_type
FROM person_visits AS pv
JOIN pizzeria AS pz ON pv.pizzeria_id = pz.id
GROUP BY pz.name
ORDER BY count DESC
LIMIT 3)
ORDER BY action_type, count DESC;