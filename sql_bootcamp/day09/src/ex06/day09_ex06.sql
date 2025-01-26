CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(
        pperson VARCHAR = 'Dmitriy',
        pprice NUMERIC = 500.0,
        pdate DATE = '2022-01-08'
    ) RETURNS TABLE(pizzeria_name VARCHAR) AS $$ BEGIN RETURN QUERY
SELECT DISTINCT pz.name AS pizzeria_name
FROM pizzeria AS pz
    JOIN person_visits AS pv ON pv.pizzeria_id = pz.id
    JOIN person AS p ON pv.person_id = p.id
    JOIN menu AS m ON pz.id = m.pizzeria_id
WHERE p.name = pperson;
END;
$$ LANGUAGE PLPGSQL;

SELECT *
FROM fnc_person_visits_and_eats_on_date(pprice := 800);

SELECT *
FROM fnc_person_visits_and_eats_on_date(
        pperson := 'Anna',
        pprice := 1300,
        pdate := '2022-01-01'
    );