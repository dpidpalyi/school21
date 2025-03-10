CREATE OR REPLACE FUNCTION fnc_trg_person_delete_audit() RETURNS TRIGGER LANGUAGE PLPGSQL AS $$ BEGIN
INSERT INTO person_audit(type_event, row_id, name, age, gender, address)
VALUES (
        'D',
        OLD.id,
        OLD.name,
        OLD.age,
        OLD.gender,
        OLD.address
    );
RETURN NULL;
END;
$$;

CREATE OR REPLACE TRIGGER trg_person_delete_audit
AFTER DELETE ON person FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_delete_audit();

DELETE FROM person
WHERE id = 10;