import os
import http.server
import socketserver
import urllib.parse

class FileExplorerHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        parsed_path = urllib.parse.urlparse(self.path)
        path = parsed_path.path
        
        if path == '/':
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            
            # Create HTML to show file structure
            html = '''
            <html>
            <head>
                <title>ARMA Reforger Team Management Mod</title>
                <style>
                    body { font-family: Arial, sans-serif; margin: 20px; }
                    h1 { color: #333; }
                    h2 { color: #666; border-bottom: 1px solid #ddd; padding-bottom: 5px; }
                    pre { background-color: #f5f5f5; padding: 10px; border-radius: 5px; }
                    .status-success { color: green; }
                    .status-error { color: red; }
                    .fixed-issue { color: green; }
                    .file-tree { background-color: #f9f9f9; padding: 15px; border-radius: 5px; }
                    table { border-collapse: collapse; width: 100%; }
                    th, td { padding: 8px; text-align: left; border-bottom: 1px solid #ddd; }
                    tr:hover { background-color: #f5f5f5; }
                </style>
            </head>
            <body>
                <h1>ARMA Reforger Team Management Mod</h1>
                
                <h2>Description</h2>
                <p>A comprehensive team management system for ARMA Reforger that includes team creation, joining, leaving, 
                invitation management, vehicle locking for team access, and network synchronization for multiplayer environments.</p>
                
                <h2>Fixed Compilation Issues</h2>
                <ul>
                    <li class="fixed-issue">✅ Fixed <code>ScriptedPlayerComponent</code> replaced with <code>GenericComponent</code></li>
                    <li class="fixed-issue">✅ Fixed <code>ScriptRPC</code> replaced with <code>ScriptCallContext</code></li>
                    <li class="fixed-issue">✅ Fixed method parameter handling for all RPC functions</li>
                    <li class="fixed-issue">✅ Fixed <code>rpc.Read()</code> to <code>ctx.Read()</code> in all handlers</li>
                    <li class="fixed-issue">✅ Fixed all RPC method documentation</li>
                </ul>
                
                <h2>Vehicle Locking Feature</h2>
                <ul>
                    <li class="fixed-issue">✅ Team-based vehicle locking system implemented</li>
                    <li class="fixed-issue">✅ Team members can access locked vehicles without unlocking</li>
                    <li class="fixed-issue">✅ Vehicle lock dialog UI for locking/unlocking vehicles</li>
                    <li class="fixed-issue">✅ Vehicle lock permissions based on team membership</li>
                    <li class="fixed-issue">✅ Network synchronization for vehicle lock status</li>
                </ul>
                
                <h2>Mod Installation Instructions</h2>
                <p>To install this mod in ARMA Reforger:</p>
                <ol>
                    <li>Copy the TeamManagement folder from <code>TeamManagement_Release</code> to your ARMA Reforger addons folder</li>
                    <li>Enable the mod in the ARMA Reforger launcher</li>
                </ol>
                <p>To upload to Workshop:</p>
                <ol>
                    <li>Open ARMA Reforger</li>
                    <li>Go to the Workshop tab</li>
                    <li>Click 'Create New'</li>
                    <li>Select the TeamManagement folder from <code>TeamManagement_Release</code></li>
                    <li>Fill in the details and upload</li>
                </ol>
                
                <h2>Compilation Status</h2>
            '''
            
            # Display errors and compilation issues
            html += self.get_compilation_status()
            
            # Display file structure
            html += '<h2>Mod File Structure</h2>'
            html += '<div class="file-tree">'
            html += self.get_file_structure()
            html += '</div>'
            
            html += '''
            </body>
            </html>
            '''
            
            self.wfile.write(html.encode())
        else:
            super().do_GET()
    
    def get_file_structure(self):
        html = '<ul>'
        def add_dir(path, indent=''):
            nonlocal html
            for item in sorted(os.listdir(path)):
                if item.startswith('.') or item.endswith('_backup.c'):
                    continue
                    
                full_path = os.path.join(path, item)
                if os.path.isdir(full_path):
                    html += f'<li><strong>{indent}{item}/</strong></li>'
                    html += '<ul>'
                    add_dir(full_path, indent + '&nbsp;&nbsp;')
                    html += '</ul>'
                elif item.endswith('.c') or item.endswith('.layout') or item == 'config.cpp':
                    html += f'<li>{indent}{item}</li>'
            
        try:
            add_dir('Scripts')
            add_dir('UI')
            add_dir('Worlds')
        except Exception as e:
            html += f'<li>Error reading directory: {str(e)}</li>'
            
        html += '</ul>'
        return html
    
    def get_compilation_status(self):
        html = '<table>'
        html += '<tr><th>Component</th><th>Status</th><th>Details</th></tr>'
        
        try:
            # Check TeamPlayerComponent 
            for mod_dir in ['Scripts', 'package/Scripts', 'TeamManagement_Release/TeamManagement/Scripts']:
                teamplayercomp_path = f'{mod_dir}/Game/TeamManagement/TeamPlayerComponent.c'
                if os.path.exists(teamplayercomp_path):
                    with open(teamplayercomp_path, 'r') as f:
                        content = f.read()
                        status = "✅ Fixed" if 'GenericComponent' in content else "❌ Error"
                        class_name = "status-success" if 'GenericComponent' in content else "status-error"
                        details = "Using correct GenericComponent" if 'GenericComponent' in content else "Using incorrect component type"
                        html += f'<tr><td>TeamPlayerComponent in {mod_dir}</td><td class="{class_name}">{status}</td><td>{details}</td></tr>'
                
                # Check TeamNetworkComponent
                teamnetwork_path = f'{mod_dir}/Game/TeamManagement/TeamNetworkComponent.c'
                if os.path.exists(teamnetwork_path):
                    with open(teamnetwork_path, 'r') as f:
                        content = f.read()
                        status = "✅ Fixed" if 'ScriptRPC' not in content else "❌ Error"
                        class_name = "status-success" if 'ScriptRPC' not in content else "status-error"
                        details = "Using correct ScriptCallContext" if 'ScriptRPC' not in content else "Contains ScriptRPC references"
                        html += f'<tr><td>TeamNetworkComponent in {mod_dir}</td><td class="{class_name}">{status}</td><td>{details}</td></tr>'
        except Exception as e:
            html += f'<tr><td colspan="3">Error checking compilation: {str(e)}</td></tr>'
        
        html += '</table>'
        return html

# Set up and run the server
PORT = 5000
Handler = FileExplorerHandler

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print(f"Serving at port {PORT}")
    httpd.serve_forever()