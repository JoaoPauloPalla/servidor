
--Database Definition
SET TIMEZONE TO 'America/Sao_Paulo';

-- User Definition
CREATE USER mqtt WITH PASSWORD 'mqttpassword';
CREATE USER api WITH PASSWORD 'apipassword';
CREATE USER front WITH PASSWORD 'frontpassword';


-- Table Definition
CREATE TABLE IF NOT EXISTS "public"."MqttUsers" (
    "id" serial NOT NULL,
    "userName" varchar(50) NOT NULL unique,
    "passwordHash" varchar(255) NOT NULL,
    "isAdmin" boolean NOT NULL DEFAULT true,
    "isActive" boolean NOT NULL DEFAULT true,
    "createdAt" timestamptz DEFAULT NOW(),
    "updatedAt" timestamptz NULL,
    PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "public"."MqttAcls" (
    "id" serial NOT NULL,
    "topic" varchar(50),
    "rw" integer CHECK ("rw" IN (0, 1, 2, 3, 4, 11, 999)) DEFAULT 0,
    "userId" integer NOT NULL,
    "createdAt" timestamptz DEFAULT NOW(),
    "updatedAt" timestamptz NOT NULL ,
    PRIMARY KEY ("id"),
    FOREIGN KEY ("userId") REFERENCES "public"."MqttUsers"("id") ON UPDATE CASCADE ON DELETE CASCADE 
);

COMMENT ON COLUMN public."MqttAcls".rw 
    IS 'Options:  0: None / 1: Read / 2: Write / 3: Read and Write / 4: Subscibe / 11: Deny / 999: all permissions';

-- Permission Definition
-- GRANT READ ON TABLE "public"."MqttAcls" TO mqtt;
-- GRANT READ ON TABLE "public"."MqttUsers" TO mqtt; 

--Insert Data
INSERT INTO "public"."MqttAcls" ( "topic", "rw", "userId") VALUES ( 'topic1', 3, '1');

INSERT INTO "public"."MqttUsers" ( "userName", "passwordHash", "isAdmin", "isActive") VALUES
( 'user1', '$2b$10$uEyoPdHpXvG.F1JhU7X5fO.6hiZqZNSh/nq4AwPVhR/oG70jRvSmS', 't', 't'),
( 'admin', '$2b$10$uEyoPdHpXvG.F1JhU7X5fO.6hiZqZNSh/nq4AwPVhR/oG70jRvSmS', 't', 't');

