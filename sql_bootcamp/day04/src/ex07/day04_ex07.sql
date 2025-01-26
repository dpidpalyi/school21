INSERT INTO person_visits
VALUES (
        (
            SELECT MAX(id) + 1
            FROM person_visits
        ),
        (
            SELECT id
            FROM person
            WHERE name = 'Dmitriy'
        ),
        (
            SELECT Z.id
            FROM menu M
                JOIN pizzeria Z ON Z.id = M.pizzeria_id
            WHERE price < 800
                AND Z.name <> 'Papa Johns'
            LIMIT 1
        ), '2022-01-08'
    );
REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;
--SELECT *
--FROM mv_dmitriy_visits_and_eats;