SELECT
  name,
  age
FROM
  person
WHERE
  gender = 'female'
  AND address LIKE '%Kazan%'
ORDER BY
  name;