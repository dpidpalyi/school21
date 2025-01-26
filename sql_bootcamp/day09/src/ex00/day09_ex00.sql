CREATE TABLE IF NOT EXISTS person_audit(
    created TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL,
    type_event CHAR(1) DEFAULT 'I' NOT NULL,
    row_id BIGINT,
    name VARCHAR,
    age INTEGER,
    gender VARCHAR,
    address VARCHAR,
    CONSTRAINT ch_type_event CHECK (type_event IN ('D', 'U', 'I'))
);

CREATE OR REPLACE FUNCTION fnc_trg_person_insert_audit() RETURNS TRIGGER LANGUAGE PLPGSQL AS $$ BEGIN
INSERT INTO person_audit(row_id, name, age, gender, address)
VALUES (
        NEW.id,
        NEW.name,
        NEW.age,
        NEW.gender,
        NEW.address
    );
RETURN NULL;
END;
$$;

CREATE OR REPLACE TRIGGER trg_person_insert_audit
AFTER
INSERT ON person FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_insert_audit();

INSERT INTO person(id, name, age, gender, address)
VALUES (10, 'Damir', 22, 'male', 'Irkutsk');