from config import Config

base = Config("127.0.0.1", "Bararide", "Nikita0642", "government")

class Database_handler:
    def __init__(self):
        pass

    def get_town_facility(self, town: str):
        with base.connection.cursor() as cursor:
            cursor.execute(
                f"SELECT * FROM government.people.town_facility WHERE facility_town = '{town}';"
            )
        
            return cursor.fetchall()

        