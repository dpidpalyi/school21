-- Session #1
BEGIN;
-- Session #2
BEGIN;
-- Session #1
UPDATE pizzeria SET name = 'Dead pizza 1' WHERE id = 1;
-- Session #2
UPDATE pizzeria SET name = 'Dead pizza 2' WHERE id = 2;
-- Session #1
UPDATE pizzeria SET name = 'Dead pizza Session #1' WHERE id = 2;
-- Session #2
UPDATE pizzeria SET name = 'Dead pizza Session #2' WHERE id = 1;
-- Session #1
COMMIT;
-- Session #2
COMMIT;