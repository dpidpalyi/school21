create table person
( id bigint primary key ,
  name varchar not null,
  age integer not null default 10,
  gender varchar default 'female' not null ,
  address varchar
  );

alter table person add constraint ch_gender check ( gender in ('female','male') );

insert into person values (1, 'Anna', 16, 'female', 'Moscow');
insert into person values (2, 'Andrey', 21, 'male', 'Moscow');
insert into person values (3, 'Kate', 33, 'female', 'Kazan');
insert into person values (4, 'Denis', 13, 'male', 'Kazan');
insert into person values (5, 'Elvira', 45, 'female', 'Kazan');
insert into person values (6, 'Irina', 21, 'female', 'Saint-Petersburg');
insert into person values (7, 'Peter', 24, 'male', 'Saint-Petersburg');
insert into person values (8, 'Nataly', 30, 'female', 'Novosibirsk');
insert into person values (9, 'Dmitriy', 18, 'male', 'Samara');


create table pizzeria
(id bigint primary key ,
 name varchar not null ,
 rating numeric not null default 0);

alter table pizzeria add constraint ch_rating check ( rating between 0 and 5);

insert into pizzeria values (1,'Pizza Hut', 4.6);
insert into pizzeria values (2,'Dominos', 4.3);
insert into pizzeria values (3,'DoDo Pizza', 3.2);
insert into pizzeria values (4,'Papa Johns', 4.9);
insert into pizzeria values (5,'Best Pizza', 2.3);
insert into pizzeria values (6,'DinoPizza', 4.2);


create table person_visits
(id bigint primary key ,
 person_id bigint not null ,
 pizzeria_id bigint not null ,
 visit_date date not null default current_date,
 constraint uk_person_visits unique (person_id, pizzeria_id, visit_date),
 constraint fk_person_visits_person_id foreign key  (person_id) references person(id),
 constraint fk_person_visits_pizzeria_id foreign key  (pizzeria_id) references pizzeria(id)
 );

insert into person_visits values (1, 1, 1, '2022-01-01');
insert into person_visits values (2, 2, 2, '2022-01-01');
insert into person_visits values (3, 2, 1, '2022-01-02');
insert into person_visits values (4, 3, 5, '2022-01-03');
insert into person_visits values (5, 3, 6, '2022-01-04');
insert into person_visits values (6, 4, 5, '2022-01-07');
insert into person_visits values (7, 4, 6, '2022-01-08');
insert into person_visits values (8, 5, 2, '2022-01-08');
insert into person_visits values (9, 5, 6, '2022-01-09');
insert into person_visits values (10, 6, 2, '2022-01-09');
insert into person_visits values (11, 6, 4, '2022-01-01');
insert into person_visits values (12, 7, 1, '2022-01-03');
insert into person_visits values (13, 7, 2, '2022-01-05');
insert into person_visits values (14, 8, 1, '2022-01-05');
insert into person_visits values (15, 8, 2, '2022-01-06');
insert into person_visits values (16, 8, 4, '2022-01-07');
insert into person_visits values (17, 9, 4, '2022-01-08');
insert into person_visits values (18, 9, 5, '2022-01-09');
insert into person_visits values (19, 9, 6, '2022-01-10');


create table menu
(id bigint primary key ,
 pizzeria_id bigint not null ,
 pizza_name varchar not null ,
 price numeric not null default 1,
 constraint fk_menu_pizzeria_id foreign key (pizzeria_id) references pizzeria(id));

insert into menu values (1,1,'cheese pizza', 900);
insert into menu values (2,1,'pepperoni pizza', 1200);
insert into menu values (3,1,'sausage pizza', 1200);
insert into menu values (4,1,'supreme pizza', 1200);

insert into menu values (5,6,'cheese pizza', 950);
insert into menu values (6,6,'pepperoni pizza', 800);
insert into menu values (7,6,'sausage pizza', 1000);

insert into menu values (8,2,'cheese pizza', 800);
insert into menu values (9,2,'mushroom pizza', 1100);

insert into menu values (10,3,'cheese pizza', 780);
insert into menu values (11,3,'supreme pizza', 850);

insert into menu values (12,4,'cheese pizza', 700);
insert into menu values (13,4,'mushroom pizza', 950);
insert into menu values (14,4,'pepperoni pizza', 1000);
insert into menu values (15,4,'sausage pizza', 950);

insert into menu values (16,5,'cheese pizza', 700);
insert into menu values (17,5,'pepperoni pizza', 800);
insert into menu values (18,5,'supreme pizza', 850);

create table person_order
(
    id bigint primary key ,
    person_id  bigint not null ,
    menu_id bigint not null ,
    order_date date not null default current_date,
    constraint fk_order_person_id foreign key (person_id) references person(id),
    constraint fk_order_menu_id foreign key (menu_id) references menu(id)
);

insert into person_order values (1,1, 1, '2022-01-01');
insert into person_order values (2,1, 2, '2022-01-01');

insert into person_order values (3,2, 8, '2022-01-01');
insert into person_order values (4,2, 9, '2022-01-01');

insert into person_order values (5,3, 16, '2022-01-04');

insert into person_order values (6,4, 16, '2022-01-07');
insert into person_order values (7,4, 17, '2022-01-07');
insert into person_order values (8,4, 18, '2022-01-07');
insert into person_order values (9,4, 6, '2022-01-08');
insert into person_order values (10,4, 7, '2022-01-08');

insert into person_order values (11,5, 6, '2022-01-09');
insert into person_order values (12,5, 7, '2022-01-09');

insert into person_order values (13,6, 13, '2022-01-01');

insert into person_order values (14,7, 3, '2022-01-03');
insert into person_order values (15,7, 9, '2022-01-05');
insert into person_order values (16,7, 4, '2022-01-05');

insert into person_order values (17,8, 8, '2022-01-06');
insert into person_order values (18,8, 14, '2022-01-07');

insert into person_order values (19,9, 18, '2022-01-09');
insert into person_order values (20,9, 6, '2022-01-10');

INSERT INTO menu
VALUES (19, 2, 'greek pizza', 800);

INSERT INTO menu
VALUES (
        (
            SELECT MAX(id) + 1
            FROM menu
        ),
        (
            SELECT id
            FROM pizzeria
            WHERE name = 'Dominos'
        ),
        'sicillian pizza',
        900
    );

INSERT INTO person_visits
VALUES ((SELECT MAX(id) + 1 FROM person_visits),
  (SELECT id FROM person WHERE name = 'Denis'),
  (SELECT id FROM pizzeria WHERE name = 'Dominos'),
  '2022-02-24'),
((SELECT MAX(id) + 2 FROM person_visits),
  (SELECT id FROM person WHERE name = 'Irina'),
  (SELECT id FROM pizzeria WHERE name = 'Dominos'),
  '2022-02-24');

INSERT INTO person_order
VALUES (
    (
      SELECT MAX(id) + 1
      FROM person_order
    ),
    (
      SELECT id
      FROM person
      WHERE name = 'Denis'
    ),
    (
      SELECT id
      FROM menu
      WHERE pizza_name = 'sicillian pizza'
        AND pizzeria_id = (
          SELECT id
          FROM pizzeria
          WHERE name = 'Dominos'
        )
    ),
    '2022-02-24'
  ),
  (
    (
      SELECT MAX(id) + 2
      FROM person_order
    ),
    (
      SELECT id
      FROM person
      WHERE name = 'Irina'
    ),
    (
      SELECT id
      FROM menu
      WHERE pizza_name = 'sicillian pizza'
        AND pizzeria_id = (
          SELECT id
          FROM pizzeria
          WHERE name = 'Dominos'
        )
    ),
    '2022-02-24'
  );

UPDATE menu SET price = price * 0.9
WHERE pizza_name = 'greek pizza';

INSERT INTO person_order
SELECT (
    SELECT MAX(id)
    FROM person_order
  ) + p.id,
  p.id,
  (
    SELECT menu.id
    FROM menu
    WHERE pizza_name = 'greek pizza'
  ),
  '2022-02-25'
FROM person AS p;

DELETE FROM person_order
WHERE order_date = '2022-02-25'
    AND menu_id = (
        SELECT id
        FROM menu
        WHERE pizza_name = 'greek pizza'
    );
DELETE FROM menu
WHERE pizza_name = 'greek pizza';

CREATE MATERIALIZED VIEW mv_dmitriy_visits_and_eats AS
SELECT pz.name
FROM pizzeria AS pz
  JOIN person_visits AS v ON v.pizzeria_id = pz.id
  JOIN person ON v.person_id = person.id
  JOIN menu ON v.pizzeria_id = menu.pizzeria_id
WHERE person.name = 'Dmitriy'
  AND v.visit_date = '2022-01-08'
  AND menu.price < 800;

INSERT INTO person_visits
VALUES (
        (
            SELECT MAX(id) + 1
            FROM person_visits
        ),
        (
            SELECT id
            FROM person
            WHERE name = 'Dmitriy'
        ),
        (
            SELECT Z.id
            FROM menu M
                JOIN pizzeria Z ON Z.id = M.pizzeria_id
            WHERE price < 800
                AND Z.name <> 'Papa Johns'
            LIMIT 1
        ), '2022-01-08'
    );
REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;
