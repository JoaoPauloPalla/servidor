db = db.getSiblingDB("BancoDados");

try {
  db.createUser({
    user: "nextapp",
    pwd: "password",
    roles: [
      {
        role: "readWrite",
        db: "data",
      },
    ],
  });

  db.createCollection("Mqtt", {
    validator: {
      $jsonSchema: {
        bsonType: "object",
        required: ["username", "password", "superuser"],
        properties: {
          username: {
            bsonType: "string",
            description: "must be a string and is required",
          },
          password: {
            bsonType: "string",
            description: "must be a string and is required",
          },
          superuser: {
            bsonType: "bool",
            description: "must be a boolean and is required",
          },
          acls: {
            bsonType: "array",
            items: {
              bsonType: "object",
              required: ["topic", "acc"],
              properties: {
                topic: {
                  bsonType: "string",
                  description: "must be a string and is required",
                },
                acc: {
                  bsonType: "int",
                  description:
                    "Options:  0: None / 1: Read / 2: Write / 3: Read and Write / 4: Subscibe / 11: Deny / 999: all permissions",
                },
              },
            },
          },
        },
      },
    },
  });

  db.Mqtt.insert({
    username: "test",
    password:
      "PBKDF2$sha512$100000$os24lcPr9cJt2QDVWssblQ==$BK1BQ2wbwU1zNxv3Ml3wLuu5//hPop3/LvaPYjjCwdBvnpwusnukJPpcXQzyyjOlZdieXTx6sXAcX4WnZRZZnw==",
    superuser: true,
    acls: [
      { topic: "test/topic/1", acc: 1 },
      { topic: "test/topic/1", acc: 4 },
      { topic: "single/topic/+", acc: 1 },
      { topic: "hierarchy/#", acc: 1 },
      { topic: "write/test", acc: 2 },
      { topic: "test/readwrite/1", acc: 3 },
    ],
  });
} catch (err) {
  print(err);
}

// // Criar o usuário com permissões de leitura e escrita na base de dados especificada
// async function createUser(username, password, databaseName, roles) {
//   try {
//     // Validação básica dos parâmetros
//     if (!username || !password || !databaseName || !roles) {
//       throw new Error("Parâmetros inválidos");
//     }

//     await db.createUser({
//       user: username,
//       pwd: password,
//       roles: roles,
//     });
//     console.log(`Usuário ${username} criado com sucesso em ${databaseName}`);
//   } catch (error) {
//     console.error("Erro ao criar usuário:", error);
//   }
// }

// // Criar as coleções
// async function createCollections() {
//   try {
//     await db[databaseName].createCollection("Mqtt", {
//       copple: true,
//       capped: true,
//       size: 1000,
//       max: 100,
//       validator: {
//         $jsonSchema: {
//           bsonType: "object",
//           required: ["username", "password", "superuser"],
//           properties: {
//             username: {
//               bsonType: "string",
//               description: "must be a string and is required",
//             },
//             password: {
//               bsonType: "string",
//               description: "must be a string and is required",
//             },
//             superuser: {
//               bsonType: "bool",
//               description: "must be a boolean and is required",
//             },
//             acls: {
//               bsonType: "array",
//               items: {
//                 bsonType: "object",
//                 required: ["topic", "acc"],
//                 properties: {
//                   topic: {
//                     bsonType: "string",
//                     description: "must be a string and is required",
//                   },
//                   acc: {
//                     bsonType: "int",
//                     description:
//                       "Options:  0: None / 1: Read / 2: Write / 3: Read and Write / 4: Subscibe / 11: Deny / 999: all permissions",
//                   },
//                 },
//               },
//             },
//           },
//         },
//       },
//     });

//     console.log(
//       `Colecões ${collectionNames} criadas com sucesso em ${databaseName}`
//     );
//   } catch (error) {
//     console.error("Erro ao criar coleções:", error);
//   }
// }

// await createUser("nextapp", "password", "database", [
//   {
//     role: "readWrite",
//     db: database,
//   },
// ]);

// await createCollections();
