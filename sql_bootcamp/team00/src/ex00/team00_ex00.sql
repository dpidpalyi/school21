DROP VIEW IF EXISTS v_search_tour;
DROP TABLE IF EXISTS graph;
CREATE TABLE graph (
    point1 VARCHAR NOT NULL,
    point2 VARCHAR NOT NULL,
    cost BIGINT NOT NULL
);
INSERT INTO graph
VALUES ('a', 'b', 10),
    ('b', 'a', 10),
    ('a', 'd', 20),
    ('d', 'a', 20),
    ('a', 'c', 15),
    ('c', 'a', 15),
    ('b', 'd', 25),
    ('d', 'b', 25),
    ('b', 'c', 35),
    ('c', 'b', 35),
    ('d', 'c', 30),
    ('c', 'd', 30);

CREATE VIEW v_search_tour AS
WITH RECURSIVE search_tour(path, cost, is_visited) AS (
    SELECT
        ARRAY[point1, point2],     -- path
        cost,                      -- cost
        point1 = point2            -- is_visited
    FROM
        graph
    WHERE point1 = 'a'
    UNION ALL
    SELECT
        src.path || dest.point2,
        src.cost + dest.cost,
        dest.point2 = ANY(src.path)
    FROM
        graph AS dest,
        search_tour AS src
    WHERE
        src.path[array_length(src.path, 1)] = dest.point1
        AND NOT src.is_visited
)
SELECT
    cost AS total_cost,
    CONCAT_WS(',', path) AS tour
FROM 
    search_tour
WHERE
    array_length(path, 1) = 5
    AND path[array_length(path, 1)] = 'a';

SELECT *
FROM
    v_search_tour
WHERE
    total_cost = (SELECT MIN(total_cost) FROM v_search_tour)
ORDER BY
    total_cost, tour;