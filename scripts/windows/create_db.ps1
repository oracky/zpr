Install-Module PSSQLite

Set-ExecutionPolicy RemoteSigned
Import-Module PSSQLite

$Database = ".\zpr.db"

$Query = "
PRAGMA foreign_keys = ON;
CREATE TABLE Cameras (
    camera_id INTEGER PRIMARY KEY,
    x_coordinate REAL,
    y_coordinate REAL,
    visibility_degree REAL
    );
CREATE TABLE Measurements (
    measurement_id INTEGER PRIMARY KEY, 
    vehicle_type INTEGER, 
    x_coordinate REAL, 
    y_coordinate REAL, 
    camera_id INTEGER,
    FOREIGN KEY (camera_id)
       REFERENCES Cameras (camera_id));"

Invoke-SqliteQuery -Query $Query -DataSource $Database
Invoke-SqliteQuery -DataSource $Database -Query "PRAGMA table_info(Cameras)"
Invoke-SqliteQuery -DataSource $Database -Query "PRAGMA table_info(Measurements)"