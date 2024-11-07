using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace NativeAotDll;

internal static class InjectionHandler
{
    internal delegate void PrintNumber(int n);

    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvStdcall)], EntryPoint = "DllMain")]
    private static bool DllMain(nint hModule, uint reason, nint reserved)
    {
        if (reason != 1)
            return false;

        Task.Run(Work);

        return true;
    }

    private static void Work()
    {
        var tempFile = Environment.GetEnvironmentVariable("TEMP") + "\\hhfdgoi438539.tmp";
        Trace.Assert(File.Exists(tempFile), "C#: Where is the temp file???");

        var hex = File.ReadAllText(tempFile);
        if (!nint.TryParse(
            hex,
            System.Globalization.NumberStyles.HexNumber,
            null,
            out var addr))
            return;

        Console.WriteLine($"C#: Address of function is {addr:X}");
        var fn = Marshal.GetDelegateForFunctionPointer<PrintNumber>(addr);
        Console.WriteLine($"C#: Got delegate for fn ptr (Type: {typeof(PrintNumber)})");

        for (var i = 1; i <= 10; i++)
        {
            Console.WriteLine($"C#: Looping #{i}");
            fn(i);
        }
    }
}
