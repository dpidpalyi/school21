CREATE INDEX idx_person_name ON person(UPPER(name));

SET enable_seqscan TO ON;
EXPLAIN ANALYZE
SELECT *
FROM person
WHERE UPPER(name) = 'DMITRIY';

SET enable_seqscan TO OFF;
EXPLAIN ANALYZE
SELECT *
FROM person
WHERE UPPER(name) = 'DMITRIY';