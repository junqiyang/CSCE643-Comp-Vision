using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            var webClient = new WebClient();
            string readHtml = webClient.DownloadString("http://128.194.140.202:8000/");
            JObject o = JObject.Parse(readHtml);

            var title = o["status"].ToString(); //stores javascriptkit.com
            Console.WriteLine(title);
            var data = o["data"].ToString();
            Console.WriteLine(title);
        }



    }
}
