USE BDLEIloes;
-- Desativar restrições de chave estrangeira para evitar erros ao eliminar tabelas que são referenciadas por outras tabelas
EXEC sp_MSforeachtable "ALTER TABLE ? NOCHECK CONSTRAINT all";

-- Eliminar tabelas
DROP TABLE IF EXISTS [dbo].[LeilaoModel];
DROP TABLE IF EXISTS [dbo].[LanceModel];
DROP TABLE IF EXISTS [dbo].[CarroModel];
DROP TABLE IF EXISTS [dbo].[BilhetePremiumModel];
DROP TABLE IF EXISTS [dbo].[AspNetUserTokens];
DROP TABLE IF EXISTS [dbo].[AspNetUsers];
DROP TABLE IF EXISTS [dbo].[AspNetUserRoles];
DROP TABLE IF EXISTS [dbo].[AspNetUserLogins];
DROP TABLE IF EXISTS [dbo].[AspNetUserClaims];
DROP TABLE IF EXISTS [dbo].[AspNetRoles];
DROP TABLE IF EXISTS [dbo].[AspNetRoleClaims];
DROP TABLE IF EXISTS [dbo].[__EFMigrationsHistory];

-- Reativar restrições de chave estrangeira
EXEC sp_MSforeachtable @command1="PRINT '?'", @command2="ALTER TABLE ? WITH CHECK CHECK CONSTRAINT all";