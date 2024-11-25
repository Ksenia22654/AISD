using System;
using System.Linq;
using System.Text;

public class OneDimensionalArray
{
    private int[] elements;

    public OneDimensionalArray(IEnumerable<int> initialElements)
    {
        elements = initialElements.ToArray();
    }

    public int this[int index]
    {
        get => elements[index];
        set => elements[index] = value;
    }

    public static OneDimensionalArray operator -(OneDimensionalArray array, int scalar)
    {
        int[] result = new int[array.elements.Length];
        for (int i = 0; i < array.elements.Length; i++)
        {
            result[i] = array.elements[i] - scalar;
        }
        return new OneDimensionalArray(result);
    }

    public static bool operator >(OneDimensionalArray array, int value)
    {
        return array.elements.All(e => e > value);
    }

    public static bool operator <(OneDimensionalArray array, int value)
    {
        return array.elements.All(e => e < value);
    }

    public static bool operator ==(OneDimensionalArray array1, OneDimensionalArray array2)
    {
        if (ReferenceEquals(array1, array2)) return true;
        if (ReferenceEquals(array1, null) || ReferenceEquals(array2, null)) return false;
        return array1.elements.SequenceEqual(array2.elements);
    }

    public static bool operator !=(OneDimensionalArray array1, OneDimensionalArray array2)
    {
        return !(array1 == array2);
    }

    public static OneDimensionalArray operator +(OneDimensionalArray array1, OneDimensionalArray array2)
    {
        int[] result = new int[array1.elements.Length + array2.elements.Length];
        array1.elements.CopyTo(result, 0);
        array2.elements.CopyTo(result, array1.elements.Length);
        return new OneDimensionalArray(result);
    }

    public override bool Equals(object obj)
    {
        if (obj is OneDimensionalArray array)
        {
            return this == array;
        }
        return false;
    }

    public override int GetHashCode()
    {
        return elements != null ? elements.GetHashCode() : 0;
    }

    public void RemoveVowelsFromString(string input)
    {
        string result = new string(input.Where(c => !"aeiouAEIOU".Contains(c)).ToArray());
        Console.WriteLine($"Строка без гласных: {result}");
    }

    public void RemoveFirstFiveElements()
    {
        if (elements.Length > 5)
        {
            int[] newArray = new int[elements.Length - 5];
            Array.Copy(elements, 5, newArray, 0, elements.Length - 5);
            elements = newArray;
        }
        else
        {
            elements = new int[0];
        }
    }

    public class Production
    {
        public int Id { get; set; }
        public string OrganizationName { get; set; }

        public Production(int id, string organizationName)
        {
            Id = id;
            OrganizationName = organizationName;
        }
    }

    public class Developer
    {
        public string FullName { get; set; }
        public int Id { get; set; }
        public string Department { get; set; }

        public Developer(string fullName, int id, string department)
        {
            FullName = fullName;
            Id = id;
            Department = department;
        }
    }

    public static class StatisticOperation
    {
        public static int Sum(OneDimensionalArray array)
        {
            return array.elements.Sum();
        }

        public static int DifferenceBetweenMaxAndMin(OneDimensionalArray array)
        {
            return array.elements.Max() - array.elements.Min();
        }

        public static int CountElements(OneDimensionalArray array)
        {
            return array.elements.Length;
        }
    }
}

public static class Extensions
{
    public static string RemoveVowels(this string input)
    {
        return new string(input.Where(c => !"aeiouAEIOU".Contains(c)).ToArray());
    }

    public static void RemoveFirstFiveElements(this OneDimensionalArray array)
    {
        array.RemoveFirstFiveElements();
    }
}

// Тестирование
public class Program
{
    public static void Main(string[] args)
    {
        OneDimensionalArray array1 = new OneDimensionalArray(new[] { 1, 2, 3, 4, 5, 6 });
        OneDimensionalArray array2 = new OneDimensionalArray(new[] { 4, 5, 6, 7, 8 });

        // Тестирование перегрузок
        var resultSubtraction = array1 - 2;
        Console.WriteLine("Результат Array1–2: " + string.Join(", ", resultSubtraction));

        bool containsValue = array1 > 3;
        Console.WriteLine($"Все элементы в Array1 больше 3: {containsValue}");

        bool arraysAreNotEqual = array1 != array2;
        Console.WriteLine($"Array1 не равен Array2: {arraysAreNotEqual}");

        var combinedArray = array1 + array2;
        Console.WriteLine("Комбинированный массив: " + string.Join(", ", combinedArray));

        // Статистика
        Console.WriteLine($"Сумма Array1: {OneDimensionalArray.StatisticOperation.Sum(array1)}");
        Console.WriteLine($"Разница между максимальным и минимальным в Array1: {OneDimensionalArray.StatisticOperation.DifferenceBetweenMaxAndMin(array1)}");
        Console.WriteLine($"Количество элементов в Array1: {OneDimensionalArray.StatisticOperation.CountElements(array1)}");

        // Применение методов расширения
        string originalString = "Hello World!";
        string stringWithoutVowels = originalString.RemoveVowels();
        Console.WriteLine($"Строка без гласных: {stringWithoutVowels}");

        array1.RemoveFirstFiveElements();
        Console.WriteLine("Array1 после удаления первых пяти элементов: " + string.Join(", ", array1));
    }
}
