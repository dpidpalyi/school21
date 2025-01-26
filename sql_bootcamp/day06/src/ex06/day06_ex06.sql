CREATE SEQUENCE seq_person_discounts AS BIGINT START WITH 1 OWNED BY person_discounts.id;

ALTER TABLE person_discounts
ALTER COLUMN id SET DEFAULT nextval('seq_person_discounts');

SELECT setval('seq_person_discounts', (SELECT MAX(id) + 1 FROM person_discounts));