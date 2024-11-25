using System;

public partial class Airline
{
    // Поля
    private string destination;
    private string flightNumber;
    private string aircraftType;
    private DateTime departureTime;
    private string[] daysOfWeek;
    private static int instanceCount;//Статическое поле для подсчета количества экземпляров класса
    private readonly int id;

    // Константы
    private const string DEFAULT_AIRCRAFT = "Boeing";

    // Характеристики
    public string Destination
    {
        get { return destination; }
        set { destination = value; }
    }

    public string FlightNumber
    {
        get { return flightNumber; }
        set { flightNumber = value; } 
    }

    public string AircraftType
    {
        get { return aircraftType; }
        set { aircraftType = value; }
    }

    public DateTime DepartureTime
    {
        get { return departureTime; }
        set { departureTime = value; }
    }

    public string[] DaysOfWeek
    {
        get { return daysOfWeek; }
        set { daysOfWeek = value; }
    }

    // Статический конструктор
    static Airline()
    {
        instanceCount = 0;
    }

    // Конструкторы
    public Airline() //Конструктор по умолчанию (без параметров)
    {
        destination = "Unknown";
        flightNumber = "0000";
        aircraftType = DEFAULT_AIRCRAFT;
        departureTime = DateTime.Now;
        daysOfWeek = new string[] { "Monday" };
        id = GetHashCode();
        instanceCount++;
    }

    public Airline(string destination, string flightNumber) //Коструктор с параметрами (с 2-мя параметрами)
    {
        this.destination = destination;
        this.flightNumber = flightNumber;
        this.aircraftType = DEFAULT_AIRCRAFT;
        this.departureTime = DateTime.Now;
        this.daysOfWeek = new string[] { "Monday" };
        id = GetHashCode();
        instanceCount++;
    }
 
    public Airline(string destination, string flightNumber, string aircraftType, DateTime departureTime, string[] daysOfWeek)
    {
        this.destination = destination;
        this.flightNumber = flightNumber;
        this.aircraftType = aircraftType;
        this.departureTime = departureTime;
        this.daysOfWeek = daysOfWeek;
        id = GetHashCode();
        instanceCount++;
    }

    // Частный конструктор
    private Airline(string destination)
    {
        this.destination = destination;
        flightNumber = "0000";
        aircraftType = DEFAULT_AIRCRAFT;
        departureTime = DateTime.Now;
        daysOfWeek = new string[] { "Monday" };
        id = GetHashCode();
        instanceCount++;
    }

    // Фабричный метод для вызова частного конструктора
    public static Airline CreateAirlineWithDestination(string destination)
    {
        return new Airline(destination);
    }

    // Методы
    public void UpdateDepartureTime(ref DateTime time, out DateTime updatedTime)
    {
        time = time.AddHours(1);
        updatedTime = time;
    }

    public override bool Equals(object obj)
    {
        if (obj is Airline airline)
        {
            return this.flightNumber == airline.flightNumber;
        }
        return false;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(destination, flightNumber, aircraftType);
    }

    public override string ToString()
    {
        return $"Flight {flightNumber} to {destination} on {aircraftType} departs at {departureTime}.";
    }

    public static void DisplayClassInfo()
    {
        Console.WriteLine($"Total Airline instances: {instanceCount}");
    }
    
} 
public class Program
{
    public static void Main(string[] args)
    {
        // Создание объектов
        Airline flight1 = new Airline();
        Airline flight2 = new Airline("New York", "NY1234");
        Airline flight3 = new Airline("London", "LD5678", "Airbus", DateTime.Now.AddHours(5), new string[] { "Monday", "Wednesday", "Friday" });
        Airline flight4 = Airline.CreateAirlineWithDestination("Tokyo");

        // Использование свойств
        flight1.Destination = "Paris";
        Console.WriteLine(flight1.Destination);

        //Использование методов
        DateTime currentTime = DateTime.Now;
        flight3.UpdateDepartureTime(ref currentTime, out DateTime updatedTime);
        Console.WriteLine($"Updated Departure Time: {updatedTime}");

        // Использование статического метода
        Airline.DisplayClassInfo();

        // Сравнение объектов
        Console.WriteLine(flight1.Equals(flight2));
        Console.WriteLine(flight2.GetHashCode());
        Console.WriteLine(flight3.ToString());

        // Тип проверки
        Console.WriteLine(flight4 is Airline);
        // Создание массива объектов авиакомпании
        Airline[] flights = new Airline[]
        {
            new Airline("Berlin", "BR123"),
            new Airline("Moscow", "MS456"),
            new Airline("Rome", "RM789")
        };

        // Показ рейсов
        foreach (var flight in flights)
        {
            Console.WriteLine(flight);
        }

        // Выполнить операцию (например, отобразить рейсы по заданному пункту назначения)
        string targetDestination = "Berlin";
        foreach (var flight in flights)
        {
            if (flight.Destination == targetDestination)
            {
                Console.WriteLine($"Flight to {targetDestination}: {flight}");
            }
        }
        {
            var anonymousFlight = new
            {
                Destination = "Sydney",
                FlightNumber = "SY1234",
                AircraftType = "Boeing",
                DepartureTime = DateTime.Now.AddHours(8),
                DaysOfWeek = new string[] { "Tuesday", "Thursday" }
            };

            Console.WriteLine($"Anonymous Flight: {anonymousFlight.FlightNumber} to {anonymousFlight.Destination} on {anonymousFlight.AircraftType} departs at {anonymousFlight.DepartureTime}.");
        };
    }
}