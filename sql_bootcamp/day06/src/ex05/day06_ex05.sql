COMMENT ON TABLE person_discounts IS 'Stores discounts in percent for each person in specified pizzeria';
COMMENT ON COLUMN person_discounts.id IS 'Unique id, PRIMARY KEY';
COMMENT ON COLUMN person_discounts.person_id IS 'Person id, FOREIGN KEY from table person';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Pizzeria id, FOREIGN KEY from table pizzeria';
COMMENT ON COLUMN person_discounts.discount IS 'Amount of the discount in percent, NUMERIC(5, 2)';