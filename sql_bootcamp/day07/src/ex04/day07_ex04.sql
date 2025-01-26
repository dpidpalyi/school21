SELECT p.name,
    COUNT(p.id) AS count_of_visits
FROM person AS p
    JOIN person_visits AS pv ON pv.person_id = p.id
GROUP BY p.name
HAVING COUNT(p.id) > 3;