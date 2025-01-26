SELECT *
FROM
    v_search_tour
WHERE
    total_cost = (SELECT MIN(total_cost) FROM v_search_tour)
    OR total_cost = (SELECT MAX(total_cost) FROM v_search_tour)
ORDER BY
    total_cost, tour;