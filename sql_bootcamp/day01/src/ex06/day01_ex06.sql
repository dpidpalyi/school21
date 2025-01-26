SELECT 
  action_date, 
  (
    SELECT 
      name AS person_name 
    FROM 
      person 
    WHERE 
      id = person_id
  ) 
FROM 
  (
    SELECT 
      order_date AS action_date, 
      person_id 
    FROM 
      person_order 
    INTERSECT 
    SELECT 
      visit_date, 
      person_id 
    FROM 
      person_visits
  ) 
ORDER BY 
  action_date, 
  person_name DESC;
