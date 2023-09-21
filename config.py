import psycopg2

class Config:
    def __init__(self, host: str, user: str, password: str, db_name: str):
        self.connection = psycopg2.connect(
            host = host,
            user = user, 
            password = password,
            database = db_name
        )

        self.connection.autocommit = True